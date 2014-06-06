<?hh // strict
namespace Fastuc\View;

/**
 * This class represents the presentation layer.
 */
class Base extends \Fastuc\Utils\TypedArray 
{
	/**
	 * @var string
	 */
	private string $template;

	/**
	 * @var \Fastuc\View\Finder
	 */
	private \Fastuc\View\Finder $finder;

	/**
	 * @param string $template
	 * @param \Fastuc\View\Finder $finder
	 */
	public function __construct( string $template = null, \Fastuc\View\Finder $finder = null )
	{
		parent::__construct();

		$this->setTemplate( $template );

		if( null === $finder )
		{
			$finder = \Fastuc\ClassLoader::getInstance()->newSingleton( '\Fastuc\View\Finder' );
		}

		$this->setTemplateFinder( $finder );
	}

	/**
	 * @return \Fastuc\View\Finder
	 */
	public function getTemplateFinder() : \Fastuc\View\Finder
	{
		return $this->finder;
	}

	/**
	 * @param \Fastuc\View\Finder
	 */
	public function setTemplateFinder( \Fastuc\View\Finder $finder ) : void
	{
		$this->finder = $finder;
	}

	/**
	 * @return string
	 */
	public function getTemplate() : string
	{
		return $this->template;
	}

	/**
	 * @param string $template
	 */
	public function setTemplate( ?string $template ) : void
	{
		$this->template = $template;
	}

	/**
	 * Renders the template into the view.
	 *
	 * @param string $template
	 * @param array $params
	 * @return string
	 */
	public function render( string $template = null, Map<string, mixed> $params = Map<string, mixed> {} ) : string
	{
		$template = ( null === $template ? $this->template : $template );
		if( empty( $template ) )
		{
			throw new Exception( 'The template has not been defined or is null.' );
		}

		$mergedParams = $this->params->setAll( $params );

		ob_start();
		$this->compose( $template, $mergedParams );
		$content = ob_get_contents();
		ob_end_clean();

		return $content;
	}

	/**
	 * Includes and renders a template. If this call is inside a render call, the output is captured and returned as string.
	 *
	 * @param string $template
	 * @param array $vars
	 */
	public function compose( string $template, Map<string, mixed> $params = Map<string, mixed> {} ) : void
	{
		$mergedParams = $this->params->setAll( $params );
		extract( $mergedParams->toArray() );

		$view = &$this;

		$templatePath = $this->finder->find( $template );
		require $templatePath;
	}
}

