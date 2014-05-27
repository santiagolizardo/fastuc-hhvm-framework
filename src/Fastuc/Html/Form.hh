<?hh // strict
namespace Fastuc\Html;

class Form extends \Fastuc\Html\Fields
{
	/**
	 * @var string
	 */
	private $action;

	/**
	 * @var string
	 */
	private $method;

	/**
	 * Encoding type.
	 *
	 * @var string
	 */
	private $encType;

	/**
	 * @var \Fastuc\Url\Base
	 */
	protected $urlFactory;

	/**
	 * Class constructor.
	 */
	public function __construct( $action = '' )
	{
		parent::__construct();

		$this->setMethod( 'post' );
		$this->setAction( $action );

		$this->urlFactory = new \Fastuc\Url\Base;

		$this->doc = new \DomDocument;
		$this->form = $this->doc->createElement( 'form' );

		$this->init();
	}

	public function setEncType( $encType )
	{
		$this->encType = $encType;
	}

	public function getEncType()
	{
		return $this->encType;
	}

	/**
	 * Form initialization (post constructor)
	 */
	public function init()
	{
	}

	public function loadValues( array $values )
	{
	}

	/**
	 * Form action setter.
	 *
	 * @param string $action
	 */
	public function setAction( $action )
	{
		$this->action = $action;
	}

	/**
	 * @return string
	 */
	public function getAction()
	{
		return $this->action;
	}

	/**
	 * Form method setter.
	 *
	 * @param string $method
	 */
	public function setMethod( $method )
	{
		if( in_array( $method, array( 'get', 'post' ) ) )
		{
			$this->method = $method;
		}
	}
	
	/**
	 * Returns the form method.
	 * 
	 * @return string
	 */
	public function getMethod()
	{
		return $this->method;
	}

	public function setAutocomplete( $autocomplete )
	{
		$this->form->setAttribute( 'autocomplete', $autocomplete );
	}

	/**
	 * @return string
	 */
	public function __toString()
	{
		$this->form->setAttribute( 'action', $this->action );
		$this->form->setAttribute( 'method', $this->method );

		if( !empty( $this->encType ) )
		{
			$this->form->setAttribute( 'enctype', $this->encType );
		}

		$childHtml = parent::__toString();
		if( !empty( $childHtml ) )
		{
			$child = $this->doc->createDocumentFragment();
			$child->appendXml( $childHtml );
			$this->form->appendChild( $child );
		}
		
		return $this->doc->saveXml( $this->form );
	}
}

