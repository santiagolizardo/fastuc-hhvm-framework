<?hh // strict
namespace Fastuc\View;

/**
 * This class extends a regular View with specific features of a HTML page.
 */
class Page extends Base 
{
	/**
	 * @var string
	 */
	private string $title;

	/**
	 * @var array
	 */
	private array $metas;

	/**
	 * @var array
	 */
	private array $links;

	private Set $javaScripts;

	/**
	 * @var \Fastuc\Url\Statics 
	 */
	protected \Fastuc\Url\Statics $staticUrls;

	/**
	 * @param string $template
	 */
	public function __construct( string $template = null )
	{
		parent::__construct();

		if( null !== $template )
		{
			$this->setTemplate( $template );
		}

		$this->title = null;

		$this->metas = array();
		$this->links = array();

		$this->javaScripts = new Set;

		$this->staticUrls = new \Fastuc\Url\Statics;
	}

	/**
	 * @param string $title
	 */
	public function setTitle( string $title ) : void
	{
		$this->title = $title;
	}

	/**
	 * @return string
	 */
	public function getTitle() : string
	{
		return $this->title;
	}

	/**
	 * @param string $keywords
	 */
	public function setMetaKeywords( string $keywords ) : void
	{
		$this->setMeta( 'keywords', $keywords );
	}

	/**
	 * @return string
	 */
	public function getMetaKeywords() : string
	{
		return $this->getMeta( 'keywords' );
	}

	/**
	 * @param string $description
	 */
	public function setMetaDescription( string $description ) : void
	{
		$this->setMeta( 'description', $description );
	}

	/**
	 * @return string
	 */
	public function getMetaDescription() : string
	{
		return $this->getMeta( 'description' );
	}

	/**
	 * Prevents this page from being indexed.
	 */
	public function disableIndexing() : void
	{
		$this->setMeta( 'robots', 'noindex,nofollow' );
	}

	/**
	 * @param string $name
	 * @param string $content
	 */
	public function setMeta( string $name, string $content ) : void
	{
		$this->metas[ $name ] = $content;
	}

	/**
	 * @return string
	 */
	public function getMeta( string $name ) : string
	{
		return isset( $this->metas[ $name ] ) ? $this->metas[ $name ] : null;
	}

	/**
	 * @return array
	 */
	public function getMetas() : array
	{
		return $this->metas;
	}

	/**
	 * @param string $javaScript
	 */
	public function addJavaScript( string $javaScript ) : void
	{
		$this->javaScripts->add( $javaScript );
	}

	/**
	 * @param array $javaScripts
	 */
	public function addJavaScripts( array $javaScripts ) : void
	{
		$this->javaScripts->addAll( $javaScripts );
	}

	/**
	 * @param Set $javaScripts
	 */
	public function setJavaScripts( Set $javaScripts ) : void
	{
		$this->javaScripts = $javaScripts;
	}

	/**
	 * @return array
	 */
	public function getJavaScripts() : Set
	{
		return $this->javaScripts;
	}

	/**
	 * @param string $rel
	 * @param string $href
	 * @param string $type
	 * @param string $media
	 * @param string $title
	 */
	public function addLink( string $rel, string $href, string $type = null, string $media = null, string $title = null )
	{
		$this->links[] = array(
			'rel' => $rel,
			'href' => $href,
			'type' => $type,
			'media' => $media,
			'title' => $title,
		);
	}

	/**
	 * @return array
	 */
	public function getLinks() : array
	{
		return $this->links;
	}

	/**
	 * @param string $styleSheet
	 */
	public function addStyleSheet( string $styleSheet ) : void
	{
		$this->addLink( 'stylesheet', $styleSheet );
	}

	/**
	 * @param array $styleSheets
	 */
	public function addStyleSheets( array $styleSheets ) : void
	{
		foreach( $styleSheets as $styleSheet )
		{
			$this->addLink( 'stylesheet', $styleSheet );
		}
	}

	public function getStyleSheets() : Set
	{
		return array_filter( $this->links, function( $link )
			{
				return ( strpos( 'stylesheet', $link['rel'] ) !== false );
			}
		);
	}

	/**
	 * @param string $mainContent
	 * @param array $vars
	 */
	public function render( string $mainContent = null, array $vars = array() ) : string
	{
		if( !empty( $mainContent ) )
		{
			$this->setParam( 'mainContent', $mainContent) ;
		}
		
		return parent::render( $mainContent, $vars );
	}
}

